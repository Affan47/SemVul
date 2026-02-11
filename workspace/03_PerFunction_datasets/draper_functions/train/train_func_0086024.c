update_state (ClutterStageX11   *stage_x11,
              ClutterBackendX11 *backend_x11,
              Atom              *state,
              gboolean           add)
{
  if (add)
    {

      XChangeProperty (backend_x11->xdpy,
                       stage_x11->xwin,
                       backend_x11->atom_NET_WM_STATE, XA_ATOM, 32,
                       PropModeReplace,
                       (unsigned char *) state, 1);
    }
  else
    {

       XDeleteProperty (backend_x11->xdpy,
                        stage_x11->xwin,
                        backend_x11->atom_NET_WM_STATE);
    }
}
