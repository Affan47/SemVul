updateDialog()
{
    const QString unitOfLength = Types::unitsOfLength().value(m_posteRazorCore->unitOfLength()).first;
    emit setCurrentUnitOfLengthSignal(unitOfLength);
    setDialogPaperOptions();
    setDialogPosterOptions();
    setDialogOverlappingOptions();
    setDialogImageInfoFields();
    setDialogSaveOptions();
    updatePreview();
}
