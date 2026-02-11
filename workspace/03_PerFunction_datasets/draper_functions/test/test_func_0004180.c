event_sluroff(t)

int t;
{
if (v->inslur) {

    addfeature(SLUR_OFF, 0, 0, 0);
    v->inslur = 0;
    }
else event_warning("No slur to close");
}
