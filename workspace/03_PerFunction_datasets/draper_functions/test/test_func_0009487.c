stop() {
    if (multi_process) {
        suspend_or_resume_descendants(false);
    } else {
        suspend_or_resume_process(pid, false);
    }
    suspended = true;
}
