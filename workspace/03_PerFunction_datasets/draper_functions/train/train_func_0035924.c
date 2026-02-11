on_action (gui::Widget *w) {
        if (w == but_ok) {
            Menu::quit();
        } else if (w == pgup) {
            if (curPage > 0) {
                curPage--;
                invalidate_all();
            }
        } else if (w == pgdown) {
            if (curPage < numPages - 1) {
                curPage++;
                invalidate_all();
            }
        }
    }
