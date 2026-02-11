element_repr(ElementObject* self)
{
    if (self->tag)
        return PyUnicode_FromFormat("<Element %R at %p>", self->tag, self);
    else
        return PyUnicode_FromFormat("<Element at %p>", self);
}
