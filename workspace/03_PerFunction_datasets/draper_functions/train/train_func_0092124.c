theme() const
{
    return d->theme ? d->theme.data() : Theme::defaultTheme();
}

}
