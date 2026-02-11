cb_connectorstyle_chooser(Fl_Choice*, void*) {

switch ( connectorstyle_chooser->value() ) {
    case 0: tree->connectorstyle(FL_TREE_CONNECTOR_NONE);     break;
    case 1: tree->connectorstyle(FL_TREE_CONNECTOR_DOTTED);   break;
    case 2: tree->connectorstyle(FL_TREE_CONNECTOR_SOLID);    break;
};
}
