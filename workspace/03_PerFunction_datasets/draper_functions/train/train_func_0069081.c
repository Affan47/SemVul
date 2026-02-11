client_set_wm_state(ObClient *self, glong state)
{
    if (state == self->wmstate) return;

    switch (state) {
    case IconicState:
        client_iconify(self, TRUE, TRUE, FALSE);
        break;
    case NormalState:
        client_iconify(self, FALSE, TRUE, FALSE);
        break;
    }
}
