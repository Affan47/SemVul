setTypes(Types type)
{
    d->m_Type = type;
    Core::Context context;
    if (type & TextEditor::CharFormat)
        context.add(Core::Constants::C_EDITOR_CHAR_FORMAT);
    if (type & TextEditor::ParagraphFormat)
        context.add(Core::Constants::C_EDITOR_PARAGRAPH);
    if (type & TextEditor::Clipboard)
        context.add(Core::Constants::C_EDITOR_CLIPBOARD);
    if (type & TextEditor::WithTables)
        context.add(Core::Constants::C_EDITOR_TABLE);
    if (type & TextEditor::WithIO)
        context.add(Core::Constants::C_EDITOR_IO);
    if (type & TextEditor::WithTextCompleter)
        context.add(Core::Constants::C_EDITOR_ADDTEXT);
    d->m_Context->setContext(context);

    d->populateToolbar();
    Core::ICore::instance()->contextManager()->updateContext();
}
