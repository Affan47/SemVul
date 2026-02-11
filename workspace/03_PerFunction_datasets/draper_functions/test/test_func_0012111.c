OnAdd(cb_unused wxCommandEvent& event)
{
    cbTool tool;
    if (DoEditTool(&tool))
    {
        Manager::Get()->GetToolsManager()->AddTool(&tool);
        DoFillList();
    }
}
