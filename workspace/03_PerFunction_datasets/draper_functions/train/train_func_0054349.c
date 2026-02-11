takeResource()
{

    if (m_canvasTaken) {
        qWarning("CanvasViewContent::takeResource: already taken");
        return QVariant();
    }


    m_canvas->setEmbeddedPainting(false);
    m_canvasTaken = true;
    Canvas * canvas = m_canvas;
    m_canvas = 0;
    update();
    return qVariantFromValue((void *)canvas);
}
