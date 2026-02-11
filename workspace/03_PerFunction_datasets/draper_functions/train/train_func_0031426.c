applyClicked()
{

    season->setName(nameEdit->text());
    season->setType(typeEdit->itemData(typeEdit->currentIndex()).toInt());
    season->setStart(fromEdit->date());
    season->setEnd(toEdit->date());
    season->setSeed(seedEdit->value());
    accept();
}
