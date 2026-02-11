_q_exposureParameterChanged(int parameter)
{
    Q_Q(QCameraExposure);

#if DEBUG_EXPOSURE_CHANGES
    qDebug() << "Exposure parameter changed:"
             << ENUM_NAME(QCameraExposureControl, "ExposureParameter", parameter)
             << exposureControl->exposureParameter(QCameraExposureControl::ExposureParameter(parameter));
#endif

    switch (parameter) {
    case QCameraExposureControl::ISO:
        emit q->isoSensitivityChanged(q->isoSensitivity());
        break;
    case QCameraExposureControl::Aperture:
        emit q->apertureChanged(q->aperture());
        break;
    case QCameraExposureControl::ShutterSpeed:
        emit q->shutterSpeedChanged(q->shutterSpeed());
        break;
    case QCameraExposureControl::ExposureCompensation:
        emit q->exposureCompensationChanged(q->exposureCompensation());
        break;
    }
}
