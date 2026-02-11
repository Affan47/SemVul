mouseButton(const MouseStroke &stroke)
{
    if (isInside(stroke.getLoc())) {
        own_mouseButton(stroke);
    }
}
