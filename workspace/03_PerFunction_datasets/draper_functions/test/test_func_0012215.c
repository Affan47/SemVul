_k_sectionSelected(int index)
{
    blockCombo->clear();
    QList<int> blocks = s_data->sectionContents(index);
    foreach(int block, blocks) {
        blockCombo->addItem(s_data->blockName(block), QVariant(block));
    }
    blockCombo->setCurrentIndex(0);
}
