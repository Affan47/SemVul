updateContext(Core::IContext *object, const Core::Context &additionalContexts)
{
    Q_UNUSED(additionalContexts);


    PadTools::Internal::PadWriter *view = 0;
    do {
        if (!object) {
            if (!m_CurrentView)
                return;
            break;
        }
        QWidget *testParents = object->widget();
        while (!view && testParents) {
            view = qobject_cast<PadTools::Internal::PadWriter *>(testParents);
            if (!view)
                testParents = testParents->parentWidget();
        }
        if (!view) {
            if (!m_CurrentView)
                return;
            break;
        }

        if (view == m_CurrentView) {
            return;
        }

    } while (false);

    if (view)
        PadToolsActionHandler::setCurrentView(view);
}
