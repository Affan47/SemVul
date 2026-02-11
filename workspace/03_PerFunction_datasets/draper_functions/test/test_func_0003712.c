updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{

    if (oldState == Stopped && newState == Running) {
        if (!m_method.isFunction()) {

            m_instance = AnimationScriptEngine::animation(m_name).construct();
            kDebug() << "trying for" << m_name << m_instance.isFunction();


            m_method = m_instance.property(QString("updateCurrentTime"));
            if (!m_method.isFunction()) {
                qDebug() << "**************** ERROR! Name: " << m_name << " ************";
                m_instance = m_method = QScriptValue();
            } else {
                prepInstance();


                qreal x = targetWidget()->geometry().height()/2;
                qreal y = targetWidget()->geometry().width()/2;
                targetWidget()->setTransformOriginPoint(x, y);
            }
        }

        if (m_method.isFunction()) {
            m_instance.setProperty("duration", duration(), QScriptValue::ReadOnly);
            m_instance.setProperty("target", m_instance.engine()->newQObject(targetWidget()), QScriptValue::ReadOnly);
        }
#ifdef PLASMA_JSANIM_FPS
        m_fps = 0;
    } else if (oldState == Running && newState == Stopped) {
        kDebug() << ".........." << m_name << " fps: " << m_fps * 1000/duration();
#endif
    }
}
