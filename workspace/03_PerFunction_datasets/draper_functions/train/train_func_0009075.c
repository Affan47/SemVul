RDFException(QString message, QString data) throw() :
    m_message(0)
{
    setMessage(QString("%1 [with string \"%2\"]").arg(message).arg(data));
}
