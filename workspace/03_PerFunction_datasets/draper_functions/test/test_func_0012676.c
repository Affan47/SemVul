signatures(bool show_return_type) const
{
    list result;
    for (function const* f = this; f; f = f->m_overloads.get()) {
        result.append(f->signature(show_return_type));
    }
    return result;
}
