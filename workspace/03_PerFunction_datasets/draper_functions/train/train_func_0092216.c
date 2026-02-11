cut()
{
    if ( m_extensionProxy )
    {
        callExtensionProxyMethod( "cut" );
        return;
    }

    if ( !m_editableFormWidget )
        return;

    QLineEdit* lineEdit = qobject_cast<QLineEdit *>( m_editableFormWidget );
    if ( lineEdit && !lineEdit->isReadOnly() )
        lineEdit->cut();
    QTextEdit* textEdit = qobject_cast<QTextEdit *>( m_editableFormWidget );
    if ( textEdit && !textEdit->isReadOnly() )
        textEdit->cut();
}
