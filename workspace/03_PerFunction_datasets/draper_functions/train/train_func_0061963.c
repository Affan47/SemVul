_get_job_uid(uint32_t jobid)
{
	List steps;
	ListIterator i;
	step_loc_t *stepd;
	slurmstepd_info_t *info = NULL;
	int fd;
	long uid = -1;

	steps = stepd_available(conf->spooldir, conf->node_name);
	i = list_iterator_create(steps);
	while ((stepd = list_next(i))) {
		if (stepd->jobid != jobid) {

			continue;
		}

		fd = stepd_connect(stepd->directory, stepd->nodename,
				   stepd->jobid, stepd->stepid);
		if (fd == -1) {
			debug3("Unable to connect to step %u.%u",
			       stepd->jobid, stepd->stepid);
			continue;
		}

		info = stepd_get_info(fd);
		close(fd);
		if (info == NULL) {
			debug("stepd_get_info failed %u.%u: %m",
			      stepd->jobid, stepd->stepid);
			continue;
		}
		uid = (long)info->uid;
		break;
	}
	list_iterator_destroy(i);
	list_destroy(steps);

	xfree(info);
	return uid;
}
