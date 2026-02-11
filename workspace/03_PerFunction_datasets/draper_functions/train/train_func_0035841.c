paintEvent(QPaintEvent *event)
{
    QPainter painter(m_widget);

    if (m_widget->testAttribute(Qt::WA_OpaquePaintEvent)) {
        QRegion borderRegion = event->region();
        borderRegion = borderRegion.subtracted(m_boundingRect);

        QBrush brush = m_widget->palette().window();

        QVector<QRect> rects = borderRegion.rects();
        for (QVector<QRect>::iterator it = rects.begin(), end = rects.end(); it != end; ++it) {
            painter.fillRect(*it, brush);
        }
    }

    if (m_surface->isActive() && m_boundingRect.intersects(event->rect())) {
        m_surface->paint(&painter, m_boundingRect, m_sourceRect);

        m_surface->setReady(true);
    } else {
 #if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_1_CL) && !defined(QT_OPENGL_ES_1)
        if (m_updatePaintDevice && (painter.paintEngine()->type() == QPaintEngine::OpenGL
                || painter.paintEngine()->type() == QPaintEngine::OpenGL2)) {
            m_updatePaintDevice = false;

            m_surface->setGLContext(const_cast<QGLContext *>(QGLContext::currentContext()));
            if (m_surface->supportedShaderTypes() & QPainterVideoSurface::GlslShader) {
                m_surface->setShaderType(QPainterVideoSurface::GlslShader);
            } else {
                m_surface->setShaderType(QPainterVideoSurface::FragmentProgramShader);
            }
        }
#endif
    }

}
