handleClick(const XButtonEvent &up, int count) {
    if ((taskBarLaunchOnSingleClick ? up.button == 2
         : up.button == 1) && count == 1)
        checkMail();
    else if (mailCommand && mailCommand[0] && up.button == 1 &&
             (taskBarLaunchOnSingleClick ? count == 1 : !(count % 2)))
        wmapp->runCommandOnce(mailClassHint, mailCommand);
}
