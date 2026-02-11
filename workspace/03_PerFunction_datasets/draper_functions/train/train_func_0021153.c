newJob(const KUrl &url, const QByteArray &packedArgs)
    {
        FileJob *job = new FileJob(*new FileJobPrivate(url, packedArgs));
        job->setUiDelegate(new JobUiDelegate);
        return job;
    }
}
