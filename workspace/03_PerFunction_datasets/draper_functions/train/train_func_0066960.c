LoadObject( const QString& uri,
                               bool persistent ) {
    if( uriObjectMap_.find( uri ) != uriObjectMap_.end() ) {
        Object* obj = uriObjectMap_[ uri ];
        return jsInterpreter_->EvaluateJavaScript( obj->jsInstanceName() );
    }
    QPluginLoader* pl = new QPluginLoader( uri );
    if( !pl->load() ) {
        const QString err = pl->errorString();
        delete pl;
        error( "Cannot load " + uri + " - " + err );
        jsInterpreter_->EvaluateJavaScript( jsErrCBack_ );
        return QVariant();
    }
    QObject* qobj = pl->instance();
    if( !qobj ) {
        delete pl;
        error( "NULL instance - " + uri );
        jsInterpreter_->EvaluateJavaScript( jsErrCBack_ );
        return QVariant();
    }
    Object* obj = qobject_cast< ::loco::Object* >( qobj );
    if( !obj ) {
        error( "Not a loco::Object, use loco::Context::LoadQtPlugin() method instead" );
        return QVariant();
    }
    obj->SetContext( this );
    obj->SetPluginLoader( pl );
    obj->setParent( pl );
    connect( obj, SIGNAL( onError( const QString& ) ), this, SLOT( OnObjectError( const QString& ) ) );
    jsInterpreter_->AddObjectToJS( obj->jsInstanceName(), obj );
    if( persistent ) {
        pl->setParent( this );
        jscriptStdObjects_.push_back( obj );
        uriObjectMap_[ uri ] = obj;
    } else {

        jsInterpreter_->AddObjectToJS( obj->jsInstanceName() + "__PluginLoader",
                                       pl, QScriptEngine::ScriptOwnership );
    }
    return jsInterpreter_->EvaluateJavaScript( obj->jsInstanceName() );
}
