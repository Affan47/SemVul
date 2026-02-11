OnbtnNoneClick(cb_unused wxCommandEvent& event)
{
    for (int i = 0; i < static_cast<int>(clbTargets->GetCount()); ++i)
    {
        clbTargets->Check(i, false);
    }
}
