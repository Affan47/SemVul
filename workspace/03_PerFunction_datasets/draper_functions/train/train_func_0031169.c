urlForFrame(QWebFrame* frame)
{
    return (frame->url().isEmpty() ? frame->baseUrl().resolved(frame->url()) : frame->url());
}
