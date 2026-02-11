InitConnectors (CNet* hnw, CNet* vnw) {
    CCnxn* hcnxn, *vcnxn;
    CNet* h = hnw->First();
    CNet* v = vnw->First();

    for (;;) {
        if (h == hnw->End()) {
            if (v == vnw->End()) {
                break;
            } else {
                vcnxn = v->Cnxn();
                v = v->Next();
                UpdateInfo(vcnxn, Vertical);
            }

        } else {
            hcnxn = h->Cnxn();
            h = h->Next();

            if (v != vnw->End()) {
                vcnxn = v->Cnxn();
                v = v->Next();
                UpdateInfo(vcnxn, Vertical);
            }
            UpdateInfo(hcnxn, Horizontal);
        }
    }
}
