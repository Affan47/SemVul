remoteAppletReady(Plasma::AccessAppletJob *job)
{
    QPointF pos = dropPoints.take(job);
    if (job->error()) {

        kDebug() << "remote applet access failed: " << job->errorText();
        return;
    }

    if (!job->applet()) {
        kDebug() << "how did we end up here? if applet is null, the job->error should be nonzero";
        return;
    }

    q->addApplet(job->applet(), pos);
}
