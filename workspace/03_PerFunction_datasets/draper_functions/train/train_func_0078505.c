Handle (Event& e) {
    if (e.eventType == KeyEvent) {
        HandleKeyEvent(e);

    } else {
        boolean done = false;

        do {
            switch (e.eventType) {
            case DownEvent:
                done = HandleDownEvent(e);
                break;

            case KeyEvent:
                done = HandleKeyEvent(e);
                break;
            }
            if (!done) {
                Read(e);
            }
        } while (!done);
    }
}
