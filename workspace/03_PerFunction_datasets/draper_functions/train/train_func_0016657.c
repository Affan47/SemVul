childrenChanged()
{


    if (!m_createdByParser && inDocument() && firstChild())
        evaluateScript(document()->URL().url(), text());
}
