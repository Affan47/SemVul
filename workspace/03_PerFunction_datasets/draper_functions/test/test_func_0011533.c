AddCharacter(txt_spincontrol_t *spincontrol, int key)
{
    if (strlen(spincontrol->buffer) < SpinControlWidth(spincontrol))
    {
        spincontrol->buffer[strlen(spincontrol->buffer) + 1] = '\0';
        spincontrol->buffer[strlen(spincontrol->buffer)] = key;
    }
}
