inRenderedText() const
{
    return RenderPosition::fromDOMPosition(*this).inRenderedContent() && node() && node()->renderer() && node()->renderer()->isText();
}
