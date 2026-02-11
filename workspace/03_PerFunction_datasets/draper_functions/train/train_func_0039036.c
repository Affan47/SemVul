netsys_forget_subprocess(value atom_idx_v) {
#ifdef HAVE_POSIX_SIGNALS
    int atom_idx;
    struct sigchld_atom *atom;

    sigchld_lock(1, 1);

    atom_idx = Int_val(atom_idx_v);
    atom = &(sigchld_list[atom_idx]);

    atom->pid = 0;
    if (!atom->ignore && !atom->terminated)
	close(atom->pipe_fd);

    sigchld_unlock(1);

    return Val_unit;
#else
    invalid_argument("Netsys_posix.forget_subprocess not available");
#endif
}
