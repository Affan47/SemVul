doDelayedHide()
{
    showTimer->stop();
    delayedHide = true;

    if (isShown && clickable) {

        hideTimer->start(1000);
    } else {
        hideTimer->start(250);
    }
}
