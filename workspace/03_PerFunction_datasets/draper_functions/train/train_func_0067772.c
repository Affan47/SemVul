open() {
    int row = world.playerRow() + player.facingY();
    int col = world.playerCol() + player.facingX();
    view.message("");

    if (Door* door = dynamic_cast<Door*>(world.itemAt(row, col))) {
        if (door->open() == true) {
            view.message("The door is already open.");
            return STATE::ERROR;
        } else {
            door->setOpen(true);
        }
        return STATE::COMMAND;
    }
    view.message("Nothing to open here.");
    return STATE::ERROR;
}
