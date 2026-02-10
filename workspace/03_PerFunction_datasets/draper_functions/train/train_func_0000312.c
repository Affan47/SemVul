Reset_IO (int destructive) {
    Discard_Input (Curr_Input_Port);
    if (destructive)
        Discard_Output (Curr_Output_Port);
    else
        Flush_Output (Curr_Output_Port);
    Curr_Input_Port = Standard_Input_Port;
    Curr_Output_Port = Standard_Output_Port;
}
