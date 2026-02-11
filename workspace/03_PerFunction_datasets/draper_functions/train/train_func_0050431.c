createWebcam(int webcamIndex, const QPoint & pos)
{
    WebcamContent * w = new WebcamContent(webcamIndex, this);
    initContent(w, pos);
    return w;
}
