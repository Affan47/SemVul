Interpret (Command* cmd) {
    if (cmd->IsA(ALIGNTOGRID_CMD)) {
        float cx, cy;
        GetGraphic()->GetCenter(cx, cy);
        ((AlignToGridCmd*) cmd)->Align(this, cx, cy);

    } else {
        GraphicView::Interpret(cmd);
    }
}
