selected(int index)
{

    home->setChecked(false);
#ifdef GC_HAVE_ICAL
    diary->setChecked(false);
#endif
    anal->setChecked(false);
    train->setChecked(false);

#ifdef GC_HAVE_ICAL
    switch (index) {
        case 0 : home->setChecked(true); break;
        case 1 : diary->setChecked(true); break;
        case 2 : anal->setChecked(true); break;
        case 3 : train->setChecked(true); break;
    }
#else
    switch (index) {
        case 0 : home->setChecked(true); break;
        case 1 : anal->setChecked(true); break;
        case 2 : train->setChecked(true); break;
    }
#endif
}
