initControls()
{
    Q_Q(QCameraExposure);

    QMediaService *service = camera->service();
    exposureControl = 0;
    flashControl = 0;
    if (service) {
        exposureControl = qobject_cast<QCameraExposureControl *>(service->requestControl(QCameraExposureControl_iid));
        flashControl = qobject_cast<QCameraFlashControl *>(service->requestControl(QCameraFlashControl_iid));
    }
    if (exposureControl) {
        q->connect(exposureControl, SIGNAL(exposureParameterChanged(int)),
                   q, SLOT(_q_exposureParameterChanged(int)));
        q->connect(exposureControl, SIGNAL(exposureParameterRangeChanged(int)),
                   q, SLOT(_q_exposureParameterRangeChanged(int)));
    }

    if (flashControl)
        q->connect(flashControl, SIGNAL(flashReady(bool)), q, SIGNAL(flashReady(bool)));
}
