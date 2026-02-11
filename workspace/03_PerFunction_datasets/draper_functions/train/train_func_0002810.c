menuShowUpdatedRegions(GtkMenuItem* , gpointer data)
{
    Gui* gui = static_cast<Gui*>(data);
    gui->showUpdatedRegions(!gui->showUpdatedRegions());


    if (!gui->showUpdatedRegions()) {
        gui->refreshView();
    }
}
