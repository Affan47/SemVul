updateBinCombinedMenu(PartsBinPaletteWidget * bin) {
    if (m_combinedMenu == NULL) return;

	m_saveBinAction->setEnabled(bin->allowsChanges());
	m_renameBinAction->setEnabled(bin->canClose());
	m_closeBinAction->setEnabled(bin->canClose());
	m_deleteBinAction->setEnabled(bin->canClose());
	ItemBase *itemBase = bin->selectedItemBase();
	bool enabled = (itemBase != NULL);
	m_editPartNewAction->setEnabled(enabled && itemBase->canEditPart());

    bool enableAnyway = false;
#ifndef QT_NO_DEBUG
    enableAnyway = true;
#endif
	m_exportPartAction->setEnabled(enabled && (!itemBase->modelPart()->isCore() || enableAnyway));
	m_removePartAction->setEnabled(enabled && bin->allowsChanges());
	m_findPartAction->setEnabled(enabled);
}
