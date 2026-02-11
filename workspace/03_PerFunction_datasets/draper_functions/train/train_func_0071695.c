Create( const QString& className, const QVariantMap& init ) {
    if( className == "ProtocolHandler" ) {
        return AddObjToJSContext( new ScriptNetworkRequestHandler );
    }
#ifdef LOCO_WKIT
    else if( className == "JavaScriptCoreContext" ) {
        Context* ctx = new Context();
        JSContext* jsCtx = new JSContext( ctx );
        ctx->setParent( jsCtx );

        ctx->Init( new WebKitJSCore(), app_, cmdLine_ );
        return AddObjToJSContext( jsCtx );
    }
#endif
#ifdef LOCO_SCRIPT
    else if( className == "QtScriptContext" ) {
        Context* ctx = new Context();
        JSContext* jsCtx = new JSContext( ctx );
        ctx->setParent( jsCtx );

        ctx->Init( new QScriptInterpreter(), app_, cmdLine_ );
        return AddObjToJSContext( jsCtx );
    }
#endif
    else if( className == "ContextThread" ) {
        ContextThread* ct = new ContextThread();
        AddQObjectToJSContext( ct, ct->JSInstanceName() );
        return jsInterpreter_->EvaluateJavaScript( ct->JSInstanceName() );
    } else if( className == "ContextThreadLoop" ) {
        ContextThreadLoop* ct = new ContextThreadLoop();
        AddQObjectToJSContext( ct, ct->JSInstanceName() );
        return jsInterpreter_->EvaluateJavaScript( ct->JSInstanceName() );
    } else if( className == "Float64Array" ) {
        return CreateArray< Float64Array >( *this, init );
    } else if( className == "Float32Array" ) {
        return CreateArray< Float32Array >( *this, init );
    } else if( className == "IntArray" ) {
        return CreateArray< IntArray >( *this, init );
    } else if( className == "UIntArray" ) {
        return CreateArray< UIntArray >( *this, init );
    } else if( className == "ShortArray" ) {
        return CreateArray< ShortArray >( *this, init );
    } else if( className == "UShortArray" ) {
        return CreateArray< UShortArray >( *this, init );
    } else if( className == "ByteArray" ) {
        return CreateArray< ByteArray >( *this, init );
    } else if( className == "ObjectArray" ) {
        QObjectArray* oa = new QObjectArray;
        return AddObjToJSContext( oa );
    } else {
        error( "Cannot create object of type " + className );
        return QVariant();
    }
}
