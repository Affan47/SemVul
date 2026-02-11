psgen_end_page(GVJ_t * job)
{
    if (job->common->show_boxes) {
	gvputs(job, "0 0 0 edgecolor\n");
	cat_libfile(job, NULL, job->common->show_boxes + 1);
    }


    gvputs(job, "endpage\nshowpage\ngrestore\n");
    gvputs(job, "%%PageTrailer\n");
    gvprintf(job, "%%%%EndPage: %d\n", job->common->viewNum);
}
