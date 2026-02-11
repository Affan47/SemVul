prepareNewPart()
{
    if (_part) {

        if (mapping == 0) return;


        _part->invalidate();
        _part->totals()->clear();
        _part->totals()->addCost(_part);
        _data->addPart(_part);
        partsAdded++;
    }

    clearCompression();
    clearPosition();

    _part = new TracePart(_data);
    _part->setName(_filename);
}
