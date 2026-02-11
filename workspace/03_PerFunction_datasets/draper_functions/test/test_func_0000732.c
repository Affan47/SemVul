deleteClicked()
{
    if (seasons->currentItem()) {
        int index = seasons->invisibleRootItem()->indexOfChild(seasons->currentItem());


        delete seasons->invisibleRootItem()->takeChild(index);

        array.removeAt(index);
    }
}
