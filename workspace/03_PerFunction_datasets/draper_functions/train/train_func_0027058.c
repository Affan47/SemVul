_q_error(int error, const QString &errorString)
{
    Q_Q(QCamera);

    this->error = QCamera::Error(error);
    this->errorString = errorString;

    qWarning() << "Camera error:" << errorString;

    emit q->error(this->error);
}
