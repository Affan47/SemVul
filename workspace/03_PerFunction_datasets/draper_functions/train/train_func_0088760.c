connectFunctions(ChildrenInterface* children) {
                Q_ASSERT( m_engine );
                Q_ASSERT( ! m_engine->hasUncaughtException() );
                QString eval;
                QScriptValue global = m_engine->globalObject();
                QHashIterator< QString, ChildrenInterface::Options > it( children->objectOptions() );
                while(it.hasNext()) {
                    it.next();
                    if( it.value() & ChildrenInterface::AutoConnectSignals ) {
                        QObject* sender = children->object(it.key());
                        if( ! sender )
                            continue;
                        QScriptValue obj = m_engine->globalObject().property(it.key());
                        if( ! obj.isQObject() )
                            continue;
                        const QMetaObject* mo = sender->metaObject();
                        const int count = mo->methodCount();
                        for(int i = 0; i < count; ++i) {
                            QMetaMethod mm = mo->method(i);
                            const QString signature = mm.signature();
                            const QString name = signature.left(signature.indexOf('('));
                            if( mm.methodType() == QMetaMethod::Signal ) {
                                QScriptValue func = global.property(name);
                                if( ! func.isFunction() ) {

                                    continue;
                                }
                                krossdebug( QString("EcmaScript::connectFunctions Connecting with %1.%2").arg(it.key()).arg(name) );
                                eval += QString("try { %1.%2.connect(%3); } catch(e) { print(e); }\n").arg(it.key()).arg(name).arg(name);
                            }
                        }
                    }
                }
                Q_ASSERT( ! m_engine->hasUncaughtException() );
                if( ! eval.isNull() ) {
                    m_engine->evaluate(eval);
                    Q_ASSERT( ! m_engine->hasUncaughtException() );
                }
            }
