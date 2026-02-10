Forward (Event& e) {
    if (IsAChild(e.target)) {
        e.target->Handle(e);
    } else {
        Handle(e);
    }
}
