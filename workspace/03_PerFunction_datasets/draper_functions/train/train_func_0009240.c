startJob(AbstractRunner *runner)
    {
        if ((runner->ignoredTypes() & context.type()) == 0) {
            FindMatchesJob *job = new FindMatchesJob(runner, &context, Weaver::instance());
            QObject::connect(job, SIGNAL(done(ThreadWeaver::Job*)), q, SLOT(jobDone(ThreadWeaver::Job*)));
            if (runner->speed() == AbstractRunner::SlowSpeed) {
                job->setDelayTimer(&delayTimer);
            }
            Weaver::instance()->enqueue(job);
            searchJobs.insert(job);
        }
    }
