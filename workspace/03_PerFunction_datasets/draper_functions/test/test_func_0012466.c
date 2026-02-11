AcpiDbDisplayHistory (
    void)
{
    UINT32                  i;
    UINT16                  HistoryIndex;


    HistoryIndex = AcpiGbl_LoHistory;


    for (i = 0; i < AcpiGbl_NumHistory; i++)
    {
        if (AcpiGbl_HistoryBuffer[HistoryIndex].Command)
        {
            AcpiOsPrintf ("%3ld  %s\n",
                AcpiGbl_HistoryBuffer[HistoryIndex].CmdNum,
                AcpiGbl_HistoryBuffer[HistoryIndex].Command);
        }

        HistoryIndex++;
        if (HistoryIndex >= HISTORY_SIZE)
        {
            HistoryIndex = 0;
        }
    }
}
