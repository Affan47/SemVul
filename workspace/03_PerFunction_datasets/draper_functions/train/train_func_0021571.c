LoadScriptFilter( const QString& id,
                                const QStringList& uriList,
                                const QString& jfun,
                                const QString& jcode,
                                const QString& jerrfun,
                                const QString& codePlaceHolder ) {
    QString code;
    for( QStringList::const_iterator i = uriList.begin(); i != uriList.end(); ++i ) {
        if( !fileAccessMgr_->CheckAccess( *i ) ) {
            error( "Access to " + *i + " not allowed" );
            return;
        }
        code += Read( *i );
    }
    Eval( code );
    Filter* lf = new ScriptFilter( jsInterpreter_, jfun, jcode, jerrfun, codePlaceHolder );
    connect( lf, SIGNAL( onError( const QString& ) ),
             this, SLOT( OnFilterError( const QString& ) ) );
    filters_[ id ] = lf;
}
