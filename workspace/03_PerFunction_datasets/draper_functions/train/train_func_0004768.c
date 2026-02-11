u_msg( const char *fmt, ...)
{


        va_list     argptr;
        QString     text;

        va_start (argptr,fmt);
        text.vsprintf(fmt, argptr);
        va_end (argptr);

        QMessageBox::information( NULL, "Info...", text, QMessageBox::Ok, QMessageBox::Ok );


}
