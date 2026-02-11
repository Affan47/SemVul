addDir(upath root, upath rdir, upath sub) {
    upath p = upath(root);
    if (rdir != null)
        p = p.relative(rdir);
    if (sub != null)
        p = p.relative(sub);
    if (p.dirExists())
        fPaths.append(new YPathElement(p));
}
