AutoComplete()
{
    LogManager* msgMan = Manager::Get()->GetLogManager();
    SAutoCompleteMap& map = GetEditorManager()->GetAutoCompleteMap();
    cbStyledTextCtrl* control = GetControl();
    int curPos = control->GetCurrentPos();
    int wordStartPos = control->WordStartPosition(curPos, true);
    wxString keyword = control->GetTextRange(wordStartPos, curPos);
    wxString lineIndent = GetLineIndentString(control->GetCurrentLine());
    msgMan->DebugLog(_T("Auto-complete keyword: ") + keyword);

    SAutoCompleteMap::iterator it;
    for (it = map.begin(); it != map.end(); ++it)
    {
        if (keyword == it->first)
        {

            msgMan->DebugLog(_T("Match found"));


            wxString code = it->second;
            code.Replace(_T("\n"), _T('\n') + lineIndent);


            bool canceled = false;
            int macroPos = code.Find(_T("$("));
            while (macroPos != -1)
            {

                int macroPosEnd = macroPos + 2;
                int len = (int)code.Length();
                while (macroPosEnd < len && code.GetChar(macroPosEnd) != _T(')'))
                    ++macroPosEnd;
                if (macroPosEnd == len)
                    break;

                wxString macroName = code.SubString(macroPos + 2, macroPosEnd - 1);
                msgMan->DebugLog(_T("Found macro: ") + macroName);
                wxString macro = wxGetTextFromUser(_("Please enter the text for \"") + macroName + _T("\":"), _("Macro substitution"));
                if (macro.IsEmpty())
                {
                    canceled = true;
                    break;
                }
                code.Replace(_T("$(") + macroName + _T(")"), macro);
                macroPos = code.Find(_T("$("));
            }

            if (canceled)
                break;

            control->BeginUndoAction();


            control->SetSelectionVoid(wordStartPos, curPos);
            control->ReplaceSelection(_T(""));
            curPos = wordStartPos;


            Manager::Get()->GetMacrosManager()->ReplaceMacros(code);

            control->InsertText(curPos, code);


            int caretPos = code.Find(_T('|'));
            if (caretPos != -1)
            {
                control->SetCurrentPos(curPos + caretPos);
                control->SetSelectionVoid(curPos + caretPos, curPos + caretPos + 1);
                control->ReplaceSelection(_T(""));
            }

            control->EndUndoAction();
            break;
        }
    }
}
