Show(bool show)
{
    if (!show)
        enableOtherWindows(true);
    return BaseDialog::Show(show);
}
