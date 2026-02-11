Init (
    ButtonState* bs, int r, int c, boolean u, int h, const char* d
) {
    const int defaultSize = 256;

    SetClassName("StringBrowser");
    input = new Sensor;
    input->Catch(DownEvent);
    input->Catch(KeyEvent);

    strbufsize = selbufsize = defaultSize;
    strbuf = new char*[strbufsize];
    selbuf = new char*[selbufsize];
    strcount = selcount = 0;

    display = nil;
    lineheight = 0;
    rows = r;
    columns = c;
    uniqueSel = u;
    singleClick = false;
    highlight = h;
    lastx = lasty = -1;
    subject = bs;
    Resource::ref(subject);
    done = d;
    perspective = new Perspective;
    InitTextDisplay();
}
