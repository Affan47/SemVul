ParseEditor(cbEditor* pEditor)
{
    if (pEditor)
        ParseBuffer(pEditor->GetControl()->GetText(), pEditor->GetFilename());
}
