updateEffectiveTime(int currentTime)
{
    if (m_method.isFunction()) {
#ifdef PLASMA_JSANIM_FPS
        ++m_fps;
#endif
        QScriptValueList args;
        args << currentTime;

        m_method.call(m_instance, args);
    }
}
