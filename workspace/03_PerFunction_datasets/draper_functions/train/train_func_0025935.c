HighlightLine( size_t line, bool highlight )
{
    bool changed;

    if ( IsVirtual() )
    {
        changed = m_selStore.SelectItem(line, highlight);
    }
    else
    {
        wxListLineData *ld = GetLine(line);
        wxCHECK_MSG( ld, false, _T("invalid index in HighlightLine") );

        changed = ld->Highlight(highlight);
    }

    if ( changed )
    {
        SendNotify( line, highlight ? wxEVT_COMMAND_LIST_ITEM_SELECTED
                                    : wxEVT_COMMAND_LIST_ITEM_DESELECTED );
    }

    return changed;
}
