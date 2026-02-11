setEncodingSettings(const QImageEncoderSettings &settings)
{
    Q_D(QCameraImageCapture);

    if (d->encoderControl) {
        QCamera *camera = qobject_cast<QCamera*>(d->mediaObject);
        if (camera && camera->captureMode() == QCamera::CaptureStillImage) {
            QMetaObject::invokeMethod(camera,
                                      "_q_preparePropertyChange",
                                      Qt::DirectConnection,
                                      Q_ARG(int, QCameraControl::ImageEncodingSettings));
        }

        d->encoderControl->setImageSettings(settings);
    }
}
