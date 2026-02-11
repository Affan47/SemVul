uc_texture_triangles( void *drv, void *dev,
                           DFBVertex *vertices, int num,
                           DFBTriangleFormation formation )
{
     UC_ACCEL_BEGIN()

     int i;

     int cmdB = HC_ACMD_HCmdB |
                HC_HVPMSK_X   | HC_HVPMSK_Y | HC_HVPMSK_Z | HC_HVPMSK_W |
                HC_HVPMSK_Cd  | HC_HVPMSK_S | HC_HVPMSK_T;

     int cmdA = HC_ACMD_HCmdA | HC_HPMType_Tri | HC_HShading_Gouraud |
                HC_HVCycle_Full;

     int cmdA_End = cmdA | HC_HPLEND_MASK | HC_HPMValidN_MASK | HC_HE3Fire_MASK;


     switch (formation) {
          case DTTF_LIST:
               cmdA |= HC_HVCycle_NewA | HC_HVCycle_NewB | HC_HVCycle_NewC;
               break;
          case DTTF_STRIP:
               cmdA |= HC_HVCycle_AB | HC_HVCycle_BC | HC_HVCycle_NewC;
               break;
          case DTTF_FAN:
               cmdA |= HC_HVCycle_AA | HC_HVCycle_BC | HC_HVCycle_NewC;
               break;
          default:
               D_ONCE( "unknown triangle formation" );
               return false;
     }

     UC_FIFO_PREPARE(fifo, 6 + num * 7);

     UC_FIFO_ADD_HDR(fifo, HC_ParaType_CmdVdata << 16);
     UC_FIFO_ADD(fifo, cmdB);
     UC_FIFO_ADD(fifo, cmdA);

     for (i=0; i<num; i++) {
          UC_FIFO_ADD_XYZWCST(fifo,
                              vertices[i].x, vertices[i].y,
                              vertices[i].z, vertices[i].w, ucdev->color3d,
                              vertices[i].s, vertices[i].t);
     }

     UC_FIFO_ADD(fifo, cmdA_End);

     UC_FIFO_PAD_EVEN(fifo);

     UC_ACCEL_END();

     return true;
}
